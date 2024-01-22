/**
 * 건물 DTO
 * 화장실이 있는 건물 정보를 저장
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class Building {
    private long buildingId; // 건물ID
    private long masterId; // 관리자ID
    private String buildingName; // 건물이름
    private double buildingLat; // 건물 위도
    private double buildingLng; // 건물 경도
    private int congestion; // 화장실혼잡도
    // 0:원활 1:혼잡 2:포화
    private String address; // 건물주소
}
