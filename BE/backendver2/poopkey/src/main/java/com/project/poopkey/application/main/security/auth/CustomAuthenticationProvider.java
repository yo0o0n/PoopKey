package com.project.poopkey.application.main.security.auth;

import com.project.poopkey.application.main.security.CustomUserDetailsService;
import org.springframework.security.authentication.AuthenticationProvider;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;

import java.util.Arrays;
import java.util.List;

public class CustomAuthenticationProvider /*implements AuthenticationProvider */ {
//    @Override
//    public Authentication authenticate(Authentication authentication) throws AuthenticationException {
//
//        // 일반 사용자의 권한을 부여하는 로직을 추가.
//
//        List<GrantedAuthority> authorities = Arrays.asList(new SimpleGrantedAuthority("ROLE"));
////        UserDetails userDetails = new CustomUserDetails(authorities);
////        return new UsernamePasswordAuthenticationToken(userDetails, authentication.getCredentials(), authorities);
//        return null;
//    }
//
//    @Override
//    public boolean supports(Class<?> authentication) {
//        return authentication.equals(UsernamePasswordAuthenticationToken.class);
//    }
}
