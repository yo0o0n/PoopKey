/**
 * 현재 칸에 휴지가 부족한 상태인지 확인할 때
 * 사용하는 DTO
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class TissueShortageStatus {
    private long stallId; // 화장실칸ID (PK)
    private int tissueStatus; // 휴지부족 여부를 나타내는 상태 여부
    // 0 : 휴지 충분, 1 : 휴지 부족
}
