package com.project.poopkey.application.main.config;

import com.project.poopkey.application.main.security.JwtAuthenticationFilter;
import com.project.poopkey.application.main.security.JwtTokenProvider;
import lombok.RequiredArgsConstructor;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configurers.CsrfConfigurer;
import org.springframework.security.config.annotation.web.configurers.HttpBasicConfigurer;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.crypto.factory.PasswordEncoderFactories;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.security.web.authentication.UsernamePasswordAuthenticationFilter;

//@Configuration
//@EnableWebSecurity
//@RequiredArgsConstructor
public class SecurityConfig {
//    private final JwtTokenProvider jwtTokenProvider;

    // 최신 스프링 시큐리티 버전에서는 기존 deprecated 표현을 람다로 교체하는 작업이 필요했다.
//    @Bean
//    public SecurityFilterChain filterChain(HttpSecurity httpSecurity) throws Exception {
//        return httpSecurity.httpBasic(HttpBasicConfigurer::disable)
//                // RESTAPI 에서는 basic auth, csrf 보안을 사용하지 않는다.
//                .csrf(CsrfConfigurer::disable)
//                // JWT를 쓸때는 세션을 사용하지 않는다.
//                .sessionManagement(config->config.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
//                .authorizeHttpRequests(authorize->
//                        authorize.requestMatchers("*").permitAll())
//                        // 시큐리티 완성 후 주석 해제
////                        authorize.requestMatchers("/sign-in").permitAll()
////                                .requestMatchers("/test").hasRole("USER")
////                                .anyRequest().authenticated())
//                // USER 권한이 있어야 접근 가능한 경우
//                // 모든 요청을 허가하는 경우
//                // 그 외에 인증이 필요한 경우
//                .addFilterBefore(new JwtAuthenticationFilter(jwtTokenProvider),
//                        UsernamePasswordAuthenticationFilter.class).build();
//    }
//
//    @Bean
//    public PasswordEncoder passwordEncoder(){
//        // BCrypt Encoder
//        return PasswordEncoderFactories.createDelegatingPasswordEncoder();
//    }

}


