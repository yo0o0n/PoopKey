package com.project.poopkey.application.main.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.util.List;

@Getter
@Setter
@ToString
public class RestroomInsert {
    private int restroomId;
    private int n; // r에 해당
    private int m; // c에 해당
    private int floor;
    private int gender;
    List<StallInsert> list;
}
