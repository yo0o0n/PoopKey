package com.project.poopkey;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.security.servlet.SecurityAutoConfiguration;
import org.springframework.context.annotation.ComponentScan;

// 아직 시큐리티 인증 부분을 구현하지 않았다.
@ComponentScan(basePackages = {"com.project.poopkey.netty","com.project.poopkey.clientsocket"})
@SpringBootApplication(exclude = SecurityAutoConfiguration.class)
public class PoopkeyApplication {

	public static void main(String[] args) {
		SpringApplication.run(PoopkeyApplication.class, args);
	}

}
