package com.project.poopkey.application.main.config;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@MapperScan(basePackages = {"com.project.poopkey.application.main.dao", "com.project.poopkey.application.render.dao"})
public class DBConfig {

}
