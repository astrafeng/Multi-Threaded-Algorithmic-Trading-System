//
// The main entry point for all downstream business logic. The server is responsible
// for creating engines and facilitating the handoff between inbound data and the
// deterministic message processing queue that feeds the engines
//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_HPP

#include <vector>
#include <future>
#include <functional>
#include <memory>

#include "StrategyEngine.hpp"
#include "MarketData/Clients/MarketDataHistoricalClient.hpp"
#include "MarketData/Clients/MarketDataLiveClient.hpp"
#include "MessageObjects/MarketData/OrderBook/Quote.hpp"
#include "CommonServer/Utils/MdTypes.hpp"
#include "CommonServer/Utils/ConcurrentQueueProcessor.hpp"

namespace BeaconTech::Strategies
{
    // Forward Declarations
    template<typename T>
    class StrategyEngine;

    template<typename T>
    class StrategyServer
    {
    private:
        int numEngineThreads;
        int numListeners;
        std::vector<StrategyEngine<T>> strategyEngines;
        std::vector<std::shared_ptr<Utils::ConcurrentQueueProcessor>> queueProcessors;
        T marketDataClient;
        MdCallback callback;

    public:
        StrategyServer();
        virtual ~StrategyServer() = default;

        void createThreads();

        int getEngineThread(const std::uint32_t& instrumentId) const;

        void subscribeToMarketData();

        void scheduleJob(int engineThreadId, const std::shared_ptr<Bbos>& bbos);
    };

} // namespace BeaconTech::Strategies


// ********** Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP
#include "StrategyServer.cpp"
#endif //#MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_HPP