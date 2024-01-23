package com.project.poopkey.model.dao;

import com.project.poopkey.model.dto.Statistics;

public interface StatisticsDao {
    public Statistics selectOne(String buildingName, int floor, int gender);
}
