package com.project.poopkey.config;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@MapperScan(basePackages = "com.project.poopkey.model.dao")
public class DBConfig {

}
