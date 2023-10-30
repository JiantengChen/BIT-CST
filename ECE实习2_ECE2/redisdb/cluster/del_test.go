package cluster

import (
	"redisdb/redis/connection"
	"redisdb/redis/protocol/asserts"
	"testing"
)

func TestDel(t *testing.T) {
	conn := connection.NewFakeConn()
	allowFastTransaction = false
	testNodeA := testCluster[0]
	testNodeA.Exec(conn, toArgs("SET", "a", "a"))
	ret := Del(testNodeA, conn, toArgs("DEL", "a", "b", "c"))
	asserts.AssertNotError(t, ret)
	ret = testNodeA.Exec(conn, toArgs("GET", "a"))
	asserts.AssertNullBulk(t, ret)
}
