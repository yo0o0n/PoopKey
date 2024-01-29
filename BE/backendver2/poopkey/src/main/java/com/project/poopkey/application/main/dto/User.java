package com.project.poopkey.application.main.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.sql.Timestamp;

@Getter
@Setter
@ToString
public class User {
    private int userId;
    private String password;
    private String email;
    private Timestamp createdDate;
}
