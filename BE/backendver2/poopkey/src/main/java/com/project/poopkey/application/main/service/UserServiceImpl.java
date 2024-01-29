package com.project.poopkey.application.main.service;

import com.project.poopkey.application.main.dao.UserDao;
import com.project.poopkey.application.main.dto.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UserServiceImpl implements UserService{

    @Autowired
    private UserDao userDao;

    @Override
    public void addUser(User user) {
        userDao.insert(user);
    }
}
