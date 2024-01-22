package com.project.poopkey.model.service;

import com.project.poopkey.model.dao.StallDao;
import com.project.poopkey.model.dto.Stall;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class StallServiceImpl implements StallService{
    @Autowired
    private StallDao stallDao;

    @Override
    public Stall findStall(long stallId) {
        return stallDao.selectOne(stallId);
    }

    @Override
    public void modifyStall(Stall stall) {
        stallDao.updateOne(stall);
    }
}
