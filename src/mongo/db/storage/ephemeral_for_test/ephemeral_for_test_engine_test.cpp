// ephemeral_for_test_engine_test.cpp


/**
 *    Copyright (C) 2018-present MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the Server Side Public License, version 1,
 *    as published by MongoDB, Inc.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    Server Side Public License for more details.
 *
 *    You should have received a copy of the Server Side Public License
 *    along with this program. If not, see
 *    <http://www.mongodb.com/licensing/server-side-public-license>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the Server Side Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#include "mongo/db/storage/ephemeral_for_test/ephemeral_for_test_engine.h"

#include "mongo/base/init.h"
#include "mongo/db/storage/kv/kv_engine_test_harness.h"
#include "mongo/stdx/memory.h"

namespace mongo {
namespace {

class EphemeralForTestKVHarnessHelper : public KVHarnessHelper {
public:
    EphemeralForTestKVHarnessHelper() : _engine(new EphemeralForTestEngine()) {}

    virtual KVEngine* restartEngine() {
        // Intentionally not restarting since the in-memory storage engine
        // does not persist data across restarts
        return _engine.get();
    }

    virtual KVEngine* getEngine() {
        return _engine.get();
    }

private:
    std::unique_ptr<EphemeralForTestEngine> _engine;
};

std::unique_ptr<KVHarnessHelper> makeHelper() {
    return stdx::make_unique<EphemeralForTestKVHarnessHelper>();
}

MONGO_INITIALIZER(RegisterKVHarnessFactory)(InitializerContext*) {
    KVHarnessHelper::registerFactory(makeHelper);
    return Status::OK();
}

}  // namespace
}  // namespace mongo
