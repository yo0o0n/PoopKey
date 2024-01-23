/**
 * 사용자가 회원가입할 때 입력하는
 * 정보를 담는 DTO
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class UserRegist {
    private long userId;
    private String email; // 사용자 이메일
    private String password; // 사용자 비밀번호
    private String phone; // 사용자 전화번호
    private String name; // 사용자 이름
}
