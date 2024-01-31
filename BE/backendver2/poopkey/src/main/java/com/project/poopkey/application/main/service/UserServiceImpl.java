package com.project.poopkey.application.main.service;

import com.project.poopkey.application.main.dao.UserDao;
import com.project.poopkey.application.main.dto.JwtToken;
import com.project.poopkey.application.main.dto.User;
import com.project.poopkey.application.main.security.JwtTokenProvider;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.core.Authentication;
import org.springframework.stereotype.Service;

@Service
//@RequiredArgsConstructor
public class UserServiceImpl implements UserService{

    @Autowired
    private UserDao userDao;

//    private final AuthenticationManagerBuilder authenticationManagerBuilder;
//
//    private final JwtTokenProvider jwtTokenProvider;

    @Override
    public void addUser(User user) {
        userDao.insert(user);
    }

//    @Override
//    public JwtToken signIn(String email, String password) {
//        UsernamePasswordAuthenticationToken authenticationToken = new UsernamePasswordAuthenticationToken(email, password);
//
//        Authentication authentication =authenticationManagerBuilder.getObject().authenticate(authenticationToken);
//
//        JwtToken jwtToken = jwtTokenProvider.generateToken(authentication);
//        return jwtToken;
//    }
}
