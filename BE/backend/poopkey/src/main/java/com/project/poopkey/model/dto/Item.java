/**
 * 비품 DTO
 * 화장실 비품에 대한 정보를 저장
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class Item {
    private long itemId; // 비품ID
    private long stallId; // 화장실칸ID
    private int tissue; // 휴지
    // 0부터 100까지 정수로 퍼센트 표시
    private int tissueChangeNumber; // 휴지교체횟수
    private int tissueStatus; // 휴지부족여부
    // 0:휴지충분, 1:휴지부족
}
