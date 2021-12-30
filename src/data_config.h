/** @file */
#ifndef DATACONFIGH
#define DATACONFIGH

#include <string_view>

/**
 * @brief  On/Off for each item in ConfigList
 */
enum class Cfg {
    DISABLED = 0,
    ACTIVE = 1
};

/** 
 * @brief  Holds configuration for a single data stream/data source.
 */
struct DataStreamConfig {
    std::string_view path; /// path from root of HDF5 data source file to data stream data
    std::string_view port; /// tcp port to send/read data from for data stream
    size_t fs; /// frequency to transmit data over (sampling frequency)
    size_t Nchannels; /// number of channels per data transmission (ie 3 for acceleration x,y,z, 1 for ECG signal)
    size_t lookback_s; /// number of timesteps in the rolling window calculations in processor
    size_t buf_size;
    Cfg status; // stream on (Cfg::ACTIVE) or off(Cfg::DISABLED)
    constexpr DataStreamConfig(const std::string_view path, const std::string_view port, const size_t fs, const size_t Nchannels, const size_t lookback_s, Cfg status) :
                               path {path}, port {port}, fs {fs}, Nchannels{Nchannels}, lookback_s{lookback_s}, buf_size{fs*lookback_s}, status{status} {}
};


constexpr size_t nsteps = 10000; /// N steps of data to send per channel for simulation; Also determines data chunk pre-read buffer size
constexpr size_t chest_fs = 700; /// Reference param for chest data sampling frequency
constexpr size_t data_queue_sz = 1024; /// Size of data queue
constexpr bool test_speed = 0; /// Triggers a data transmission speed test
constexpr bool debug_recv = 0; /// Debugs recv data in Server application
constexpr size_t hr_moving_avg_window = 10;
constexpr size_t print_state_delay_ms = 1000;
/** 
 * @brief  List of DataStreamConfigs.
 *                                                 |      PATH       |           PORT           |   fs   | Nchannels | Lookback (s) | On/off |
 *                                          =====================================================================================
 */
constexpr std::array ConfigList {DataStreamConfig  {"/signal/chest/ACC",  "tcp://127.0.0.1:5000", chest_fs, 3,        5,            Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/chest/ECG",  "tcp://127.0.0.1:5001", chest_fs, 1,        5,            Cfg::ACTIVE},
                                 DataStreamConfig  {"/signal/chest/EMG",  "tcp://127.0.0.1:5002", chest_fs, 1,        5,            Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/chest/EDA",  "tcp://127.0.0.1:5003", chest_fs, 1,        5,            Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/chest/Temp", "tcp://127.0.0.1:5004", chest_fs, 1,        5,            Cfg::DISABLED}, // *32 bit int
                                 DataStreamConfig  {"/signal/chest/Resp", "tcp://127.0.0.1:5005", chest_fs, 1,        5,            Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/wrist/ACC",  "tcp://127.0.0.1:5006", 32,       3,        60,           Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/wrist/BVP",  "tcp://127.0.0.1:5007", 64,       1,        60,           Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/wrist/EDA",  "tcp://127.0.0.1:5008", 4,        1,        60,           Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/wrist/TEMP", "tcp://127.0.0.1:5009", 4,        1,        60,           Cfg::DISABLED}};

constexpr std::array FeatureList {"chestACCMean",
                                  "chestACCStd",
                                //"chestACC0Mean",
                                //"chestACC0Std",
                                //"chestACC0Freq",
                                //"chestACC1Mean",
                                //"chestACC1Std",
                                //"chestACC1Freq",
                                //"chestACC2Mean",
                                //"chestACC2Std",
                                //"chestACC2Freq",
                                  "chestECGMeanHR",
                                  "chestECGStdHR",
                                  "chestECGMeanHRV",
                                  "chestECGStdHRV",
                                  // "chestECGTINN",
                                  // "chestECGRMS",
                                  "chestEMGMean",
                                  "chestEMGStd",
                                  "chestEMGFq",
                                  "chestEDAMean",
                                  // "chestEDAMax",
                                  // "chestEDAMin",
                                  // "chestEDADyn",
                                  "chestTempMean",
                                  // "chestTempMax",
                                  // "chestTempMin",
                                  // "chestTempDyn",
                                  // "chestResp",
                                  "wristACCMean",
                                  "wristACCMax",
                                  "wristACCMin",
                                  "wristBVPMeanHR",
                                  "wristBVPStdHR",
                                  "wristBVPMeanHRV",
                                  "wristBVPStdHRV",
                                  // "wristBVPTINN",
                                  // "wristBVPRMS",
                                  "wristEDAMean",
                                  // "wristEDAMax",
                                  // "wristEDAMin",
                                  // "wristEDADyn",
                                  "wristTEMPMean",
                                  // "wristTEMPMax",
                                  // "wristTEMPMin",
                                  // "wristTEMPDyn"
                                  };
constexpr size_t NumberOfFeatures = std::size(FeatureList);
#endif // DATACONFIGH
