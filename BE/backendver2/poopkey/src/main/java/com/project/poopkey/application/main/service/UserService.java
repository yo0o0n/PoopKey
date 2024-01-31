package com.project.poopkey.application.main.service;

import com.project.poopkey.application.main.dto.JwtToken;
import com.project.poopkey.application.main.dto.User;

public interface UserService {
    void addUser(User user);

//    JwtToken signIn(String email, String password);
}
