/**
 * 관리자 DTO
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class Master {
    private long masterId; // 관리자 ID
    private String password; // 비밀번호 (Hash한 값으로 처리)
    private String name; // 이름
    private String phone; // 휴대폰 번호
    private String deviceId; // 기기ID

}
