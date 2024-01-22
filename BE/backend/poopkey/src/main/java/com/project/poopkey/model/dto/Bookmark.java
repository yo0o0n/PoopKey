/**
 * 북마크 DTO
 * 회원가입한 사용자가 자주 찾아가는 건물명을
 * 북마크로 저장해둠
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.sql.Timestamp;

@Getter
@Setter
@ToString
public class Bookmark {
    private long bookmarkId; // 북마크ID
    private long userId; // 사용자ID
    private Timestamp createdDate; // 등록날짜
    private String content; // 북마크 내용
}
