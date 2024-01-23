package com.project.poopkey.model.dao;

import com.project.poopkey.model.dto.ToiletBreakStatus;

public interface ToiletBreakStatusDao {
    /**현재 변기가 고장났는지 상태를 표시할 때 사용*/
    public ToiletBreakStatus selectOne(long stallId);
}
