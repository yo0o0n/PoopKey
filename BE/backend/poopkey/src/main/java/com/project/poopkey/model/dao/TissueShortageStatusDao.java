package com.project.poopkey.model.dao;

import com.project.poopkey.model.dto.TissueShortageStatus;

public interface TissueShortageStatusDao {
    /**휴지가 부족한 상태인지 확인할 때 사용하는 메서드*/
    public TissueShortageStatus selectOne(long stallId);
}
