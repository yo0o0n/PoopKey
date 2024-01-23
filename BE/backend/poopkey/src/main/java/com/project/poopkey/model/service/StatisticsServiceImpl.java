package com.project.poopkey.model.service;

import com.project.poopkey.model.dao.StatisticsDao;
import com.project.poopkey.model.dto.Statistics;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class StatisticsServiceImpl implements StatisticsService{

    @Autowired
    private StatisticsDao statisticsDao;

    @Override
    public Statistics findStatistics(String buildingName, int floor, int gender) {
        return statisticsDao.selectOne(buildingName, floor, gender);
    }
}
