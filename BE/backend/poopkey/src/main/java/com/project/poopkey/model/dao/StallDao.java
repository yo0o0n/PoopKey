package com.project.poopkey.model.dao;

import com.project.poopkey.model.dto.Stall;
public interface StallDao {
    /** 화장실 칸 세부정보 표시(공통) */
    public Stall selectOne(long stallId);
    /**관리자가 화장실 칸 상태 변경(점검중..)*/
    public void updateOne(Stall stall);
}
