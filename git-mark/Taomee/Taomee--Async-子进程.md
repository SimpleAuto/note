``` c++
void run_worker_process(bind_config_t* bc, int bc_elem_idx, int n_inited_bc)
{
    // 配置文件
    bind_config_elem_t* bc_elem = &(bc->configs[bc_elem_idx]);

    char prefix[10] = { 0 };
    int  len       = snprintf(prefix, 8, "%u", bc_elem->online_id);
    prefix[len] = '_';

#ifdef USE_TLOG
    char prefix_1[10] = { 0 };
    snprintf(prefix_1, 10, "%d", bc_elem->online_id);
    INIT_DEFAULT_LOGGER_SYSTEM( config_get_strval("log_dir"),
                                prefix_1,
                                config_get_strval("project_name"),
                                config_get_intval("project_id", 0),
                                config_get_strval("svc_type")
                                );
    // INIT_DEFAULT_LOGGER_SYSTEM底层调用了3个函数
    // 1 init_logger_ctrl_cfg  控制logger行为的一些参数,控制多少秒切换一次log文件
    // 2 init_logger_svc_info  记录logger来源服务器的ip以及服务名称
    // 3 init_logger           创建logger目录,设置文件名格式
    // USE_TLOG 作用是程序启动的时候,监听的fd是否添加成功,往日志中输出服务以及ip信息
    int log_time_interval = config_get_intval("tlog_file_interval_sec", 900);
    if (log_time_interval < 0 || log_time_interval > 86400) {
        log_time_interval = 900;
    }
    SET_MAX_ONE_SIZE(100);
    SET_TIME_SLICE_SECS(log_time_interval);
    SET_LOG_LEVEL(config_get_intval("log_level", tlog_lvl_debug));
#endif

    // 基础Log设置
    // log_init 业务日志设置,根据log等级生成日志级别,最终调用write写入文件操作
    log_init_ex( config_get_strval("log_dir"),
                config_get_intval("log_level", log_lvl_trace),
                config_get_intval("log_size", 1<<30),
                config_get_intval("max_log_files", 100),
                prefix ,
                config_get_intval("log_save_next_file_interval_min", 0) );
    is_parent = 0;

    // release resources inherited from parent process
    // 释放从父进程继承的资源
    close_shmq_pipe(bc, n_inited_bc, 1);
    shmq_destroy(bc_elem, n_inited_bc);
    net_exit();

    // 进程的name和id进行绑定
    daemon_set_title("%s-%u", prog_name, bc_elem->online_id);

    // epoll_create 注册监听的fd数目
    net_init(max_fd_num, 2000);
    // 添加FD
    do_add_conn(bc_elem->recvq.pipe_handles[0], fd_type_pipe, 0, 0);

    // 初始化句柄,创建socket并添加到epoll池中,绑定对应IP和端口
    if ( handle_init(bc_elem) != 0 ) {
      ERROR_LOG("fail to init worker process. olid=%u olname=%s", bc_elem->online_id, bc_elem->online_name);
      goto fail;
    }

    int timeout = config_get_intval("net_loop_interval", 100);
    if (timeout < 0 || timeout > 1000)
          timeout = 100;//用户自定义业务进程的netloop时间

    while ( !stop || !handle_fini() ) {
      // 等包 epoll_wait
      net_loop(timeout, page_size, 0);
    }

fail:
    do_destroy_shmq(bc_elem);
    net_exit();
    unregister_data_plugin();
    unregister_plugin();
    free_argv();
    free(prog_name);
    free(current_dir);

    exit(0);
}

```

### epoll相关
