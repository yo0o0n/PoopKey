package com.project.poopkey.controller;

import com.project.poopkey.model.dto.UserRegist;
import com.project.poopkey.model.service.UserRegistService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api")
@CrossOrigin("*")
public class UserRegistController {

    @Autowired
    private UserRegistService userRegistService;

    @PostMapping("/user/regist")
    public ResponseEntity<Void> userRegistAdd(@RequestBody UserRegist userRegist){
        userRegistService.addUserRegist(userRegist);
        return new ResponseEntity<Void>(HttpStatus.CREATED);
    }
}
