/**
 * OPEN API로 다른 개발자들을 위해
 * 화장실 사용통계정보를 제공할 때 사용하는
 * DTO(VO) 객체
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.util.List;

@Getter
@Setter
@ToString
public class Statistics {
    private String buildingName; // 건물이름
    private int floor; // 화장실 층수
    private int gender; // 성별 (남:0, 여:1)
    List<StatisticsStall> stallList; // 화장실 각 칸에 대한 정보

}
