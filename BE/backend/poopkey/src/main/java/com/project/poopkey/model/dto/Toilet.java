/**
 * 변기 DTO
 * 변기에 대한 정보를 저장
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class Toilet {
    private long toiletId;
    private long stallId;
    private int status;
    // 변기막힘 여부는 화장실 칸 table의 고장 column으로 반영된다.
}
