package com.project.poopkey.model.service;

import com.project.poopkey.model.dao.UserRegistDao;
import com.project.poopkey.model.dto.UserRegist;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UserRegistServiceImpl implements  UserRegistService{

    @Autowired
    private UserRegistDao userRegistDao;

    @Override
    public void addUserRegist(UserRegist userRegist) {
        userRegistDao.insert(userRegist);
    }
}
