/**
 * 화장실 DTO
 * 화장실 한 칸에 대한 정보를 저장
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.sql.Timestamp;

@Getter
@Setter
@ToString
public class Stall {
    private long stallId; // 화장실칸ID
    private long restroomId; // 화장실ID
    private int status; // 화장실칸 상태
    // 사용가능:0 사용중:1 고장:2 점검:3 고장의심:4
    private Timestamp lastUsedTime; // 화장실을 사용했을 때 갱신
    private int closed; // 잠김여부
    private int able; // 사용가능여부
    // 0:사용가능 1:사용불가
    private int usedNumberAfterCleaning; // 청소후 사용횟수
    // 청소후 0으로 reset
    private int usedNumber; // 사용횟수
    private int breakNumber; // 고장횟수
    private int cleaning; //  청소중 여부
//    0:청소x 1:청소중
    private int stallNumber; // 화장실칸번호
    // 1부터 시작하는 화장실 번호
}
