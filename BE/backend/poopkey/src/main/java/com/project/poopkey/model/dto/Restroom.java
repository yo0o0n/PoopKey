/**
 * 화장실 DTO
 * 화장실에 대한 정보를 저장
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.sql.Timestamp;

@Getter
@Setter
@ToString
public class Restroom {
    private long restroomId; // 화장실ID
    private long buildingId; // 건물ID
    private int floor; // 층수
    private int congestion; // 혼잡도
    private int gender; // 성별 0:남성 1:여성
    private int cleaning; // 청소중여부 0:청소x 1:청소중
    private int height; // 그리드 행수
    private int width; // 그리드 열수
    private Timestamp lastCleaningTime; // 마지막청소시간
}
