#ifndef KINESIS_PRODUCER_HPP
#define KINESIS_PRODUCER_HPP

#include <aws/core/Aws.h>
#include <aws/core/utils/HashingUtils.h>
#include <aws/kinesis/KinesisClient.h>
#include <aws/kinesis/model/PutRecordRequest.h>
#include <aws/kinesis/model/PutRecordRequest.h>
#include <aws/core/utils/Outcome.h>

#include <string>

namespace eosio {
const char *kSTREAM_NAME = "EOS_Asia_Kinesis";
const char *kREGION_NAME = "ap-northeast-1";

class kinesis_producer {
 public:
  kinesis_producer() {}

  int kinesis_init(const std::string& stream_name, const std::string& region_name) {
    // m_options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info; // Turn on log.
    Aws::InitAPI(m_options);

    Aws::Client::ClientConfiguration clientConfig;
    // set your region
    clientConfig.region = Aws::Utils::HashingUtils::HashString(region_name);
    m_regionName = stream_name;
    m_client = new Aws::Kinesis::KinesisClient(clientConfig);
    return 0;
  }

  int kinesis_sendmsg(int trxtype, unsigned char *msgstr, size_t length) {
    // trxtype => to different stream.
    Aws::Kinesis::Model::PutRecordRequest request;
    request.SetStreamName(m_streamName);
    Aws::Utils::ByteBuffer data(msgstr, length);
    request.SetData(data);

    auto result = m_client->PutRecord(request);
    if (!result.IsSuccess()) {
      return 1;
    }
    return 0;
  }

  int kinesis_destory() {
    delete m_client;
    Aws::ShutdownAPI(m_options);
    return 0;
  }
  
 private:
  Aws::SDKOptions m_options;
  Aws::Kinesis::KinesisClient *m_client;
  Aws::String m_streamName;
};

}  // namespace eosio

#endif
