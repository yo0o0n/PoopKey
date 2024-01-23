/**
 * 변기고장 여부출력 API에 사용됨
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class ToiletBreakStatus {
    private long stallId;
    private int status;
}
