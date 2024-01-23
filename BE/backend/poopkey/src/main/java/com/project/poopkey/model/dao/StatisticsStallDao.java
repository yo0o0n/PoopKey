package com.project.poopkey.model.dao;

import com.project.poopkey.model.dto.StatisticsStall;

import java.util.List;

public interface StatisticsStallDao {
    /**제공하는 OpenAPI에서 선택된 화장실 칸에 대한 정보들을 가져올 때 사용하는 Dao*/
    public List<StatisticsStall> selectList(long restroomId);
}
