/**
 * Master로부터 입력받은 건물 정보를 등록할 때 사용하는 DTO
 * */
package com.project.poopkey.application.main.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.util.List;

@Getter
@Setter
@ToString
public class RestroomInfoInsert {
    private int buildingId;
    private int floor;
    private int gender;
    private int height;
    private int width;
    List<StallInfoInsert> list;
}
