/**
 * 블록 DTO
 * 빈칸, 화장실칸, 입구칸을 보여주는 화장실 블록 정보를 담음
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class Block {
    private long blockId; // 블록ID
    private long restroomId; // 화장실ID
    private int row; // 행번호
    private int col; // 열번호
    private int content; // 그 칸의 내용
    // 0:빈칸, 1:화장실, 2:입구
}
