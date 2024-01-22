/**
 * 신고 DTO
 * 센서, 사용자로부터 들어온 신고정보를 저장
 * */
package com.project.poopkey.model.dto;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.sql.Timestamp;

@Getter
@Setter
@ToString
public class Report {
    private long reportId; // 신고ID
    private long stallId; // 화장실칸ID
    private long restroomId; // 화장실ID
    private String content; // 신고내용
    private Timestamp createdDate; // 생성일
    private int userReportReason; // 신고사유
    // 위생:0 파손:1 기타:2
}
