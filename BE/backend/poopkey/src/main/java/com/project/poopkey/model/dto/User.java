/**
 * 사용자 DTO
 * 사용자에 대한 정보를 저장
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.sql.Timestamp;

@Getter
@Setter
@ToString
public class User {
    private long userId; // 사용자ID
    private String password; // 비밀번호
    private String email; // 이메일 주소가 아이디역할
    private String phone; // 휴대폰번호
    private Timestamp createdDate; // 생성일
    private String number; // 이름
    private byte[] profile; // 프로필사진, longblob
    // 이미지파일을 binary 형태로 DB에 저장.
    // 기본 이미지파일 준비하기
    private String addresss; // 주소
}
