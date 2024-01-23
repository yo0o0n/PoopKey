package com.project.poopkey.model.service;

import com.project.poopkey.model.dto.Statistics;

public interface StatisticsService {
    Statistics findStatistics(String buildingName, int floor, int gender);
}
