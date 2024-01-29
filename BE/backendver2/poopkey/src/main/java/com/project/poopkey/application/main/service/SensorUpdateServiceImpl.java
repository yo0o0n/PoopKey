package com.project.poopkey.application.main.service;

import com.project.poopkey.application.main.dao.ItemSensorUpdateDao;
import com.project.poopkey.application.main.dao.RestroomSensorUpdateDao;
import com.project.poopkey.application.main.dao.StallSensorUpdateDao;
import com.project.poopkey.application.main.dao.StatisticSensorUpdateDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class SensorUpdateServiceImpl implements SensorUpdateService{

    @Autowired
    private ItemSensorUpdateDao itemSensorUpdateDao;

    @Autowired
    private RestroomSensorUpdateDao restroomSensorUpdateDao;

    @Autowired
    private StallSensorUpdateDao stallSensorUpdateDao;

    @Autowired
    private StatisticSensorUpdateDao statisticSensorUpdateDao;

    @Override
    public void modifyTissue(long stallId, int tissue) {
        statisticSensorUpdateDao.updateTissue(stallId, tissue);
        itemSensorUpdateDao.update(stallId, tissue);
    }


    @Override
    public void modifyOccupied(long stallId) {
        stallSensorUpdateDao.updateOccupied(stallId);
        statisticSensorUpdateDao.updateOccupied(stallId);
    }

    @Override
    public void modifyVacant(long stallId) {
        stallSensorUpdateDao.updateVacant(stallId);
    }

    @Override
    public void modifyBreak(long stallId) {
        stallSensorUpdateDao.updateBreak(stallId);
        statisticSensorUpdateDao.updateBreak(stallId);
    }

    @Override
    public void modifyCongestion(int restroomId, int congestion) {
        restroomSensorUpdateDao.updateCongestion(restroomId, congestion);
    }


}
