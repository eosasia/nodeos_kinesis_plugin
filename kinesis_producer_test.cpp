#include "include/eosio/kinesis_plugin/kinesis_producer.hpp"

int main(int argc, char **argv)
{
	unsigned char buf[512] = "abcdefghijkl";
    eosio::kinesis_producer producer;
    producer.kinesis_init();

    producer.kinesis_sendmsg(1, buf, 12);

    producer.kinesis_destory();
}
