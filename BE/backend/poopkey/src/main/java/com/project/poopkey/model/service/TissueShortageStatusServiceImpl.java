package com.project.poopkey.model.service;

import com.project.poopkey.model.dao.TissueShortageStatusDao;
import com.project.poopkey.model.dto.TissueShortageStatus;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class TissueShortageStatusServiceImpl implements TissueShortageStatusService{

    @Autowired
    private TissueShortageStatusDao tissueShortageStatusDao;

    @Override
    public TissueShortageStatus findTissueShortageStatus(long stallId) {
        return tissueShortageStatusDao.selectOne(stallId);
    }
}
