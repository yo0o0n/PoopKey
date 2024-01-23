package com.project.poopkey.model.dto.render;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class FloorCongestion {
    private long buildingId; // 건물아이디. DB select에 사용
    private int floor;
    private int gender;
    private int congestion; // 혼잡도
}
