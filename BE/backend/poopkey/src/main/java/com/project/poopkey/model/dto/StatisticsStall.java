package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.sql.Timestamp;

@Getter
@Setter
@ToString
public class StatisticsStall {
    private int stallNumber; // 화장실 칸 번호(1부터 시작하는 그 화장실에 대한 번호 인덱스, PK가 아님)
    private int usedNumber; // 화장실 칸 사용 횟수
    private int breakNumber; // 화장실 칸 고장 횟수
    private Timestamp lastCleaningTime; // 화장실 마지막 청소시간
    private int tissueChangeNumber; // 휴지 교체 횟수
}
