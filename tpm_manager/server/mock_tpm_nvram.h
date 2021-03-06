//
// Copyright (C) 2015 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef TPM_MANAGER_SERVER_MOCK_TPM_NVRAM_H_
#define TPM_MANAGER_SERVER_MOCK_TPM_NVRAM_H_

#include "tpm_manager/server/tpm_nvram.h"

#include <map>
#include <string>

#include <gmock/gmock.h>

namespace tpm_manager {

struct NvSpace {
  std::string data;
  bool read_locked;
  bool write_locked;
  std::vector<NvramSpaceAttribute> attributes;
  std::string authorization_value;
  NvramSpacePolicy policy;
};

class MockTpmNvram : public TpmNvram {
 public:
  MockTpmNvram();
  ~MockTpmNvram() override;

  MOCK_METHOD5(DefineSpace,
               NvramResult(uint32_t,
                           size_t,
                           const std::vector<NvramSpaceAttribute>&,
                           const std::string&,
                           NvramSpacePolicy));
  MOCK_METHOD1(DestroySpace, NvramResult(uint32_t));
  MOCK_METHOD3(WriteSpace,
               NvramResult(uint32_t, const std::string&, const std::string&));
  MOCK_METHOD3(ReadSpace,
               NvramResult(uint32_t, std::string*, const std::string&));
  MOCK_METHOD4(LockSpace,
               NvramResult(uint32_t, bool, bool, const std::string&));
  MOCK_METHOD1(ListSpaces, NvramResult(std::vector<uint32_t>*));
  MOCK_METHOD6(GetSpaceInfo,
               NvramResult(uint32_t,
                           size_t*,
                           bool*,
                           bool*,
                           std::vector<NvramSpaceAttribute>*,
                           NvramSpacePolicy*));

 private:
  NvramResult FakeDefineSpace(
      uint32_t index,
      size_t size,
      const std::vector<NvramSpaceAttribute>& attributes,
      const std::string& authorization_value,
      NvramSpacePolicy policy);
  NvramResult FakeDestroySpace(uint32_t index);
  NvramResult FakeWriteSpace(uint32_t index,
                             const std::string& data,
                             const std::string& authorization_value);
  NvramResult FakeReadSpace(uint32_t index,
                            std::string* data,
                            const std::string& authorization_value);
  NvramResult FakeLockSpace(uint32_t index,
                            bool lock_read,
                            bool lock_write,
                            const std::string& authorization_value);
  NvramResult FakeListSpaces(std::vector<uint32_t>* index_list);
  NvramResult FakeGetSpaceInfo(uint32_t index,
                               size_t* size,
                               bool* is_read_locked,
                               bool* is_write_locked,
                               std::vector<NvramSpaceAttribute>* attributes,
                               NvramSpacePolicy* policy);

  std::map<uint32_t, NvSpace> nvram_map_;
};

}  // namespace tpm_manager

#endif  // TPM_MANAGER_SERVER_MOCK_TPM_NVRAM_H_
