//
// Created by Michael Lewis on 9/28/23.
//

#include <memory>

#include <databento/historical.hpp>
#include <databento/fixed_price.hpp>

#include "MarketDataHistoricalClient.hpp"
#include "MarketDataStreamingClient.hpp"
#include "MarketDataUtils.hpp"

namespace MarketData
{
    databento::KeepGoing processQuote(const databento::Record& record)
    {
        auto mboMsg = record.Get<databento::MboMsg>();
        auto size = mboMsg.size;
        auto price = float(mboMsg.price) / float(databento::kFixedPriceScale);
        auto side = mboMsg.side;
        std::cout << mboMsg.hd.instrument_id << '\t' << size << '\t' << price << '\t' << side << '\n';
        return databento::KeepGoing::Continue;
    }

    MarketDataHistoricalClient::MarketDataHistoricalClient() : IMarketDataProvider{}, client{}
    {
        streamingClient = std::make_shared<MarketDataStreamingClient<MarketDataHistoricalClient>>(*this);
        initialize();
    }

    void MarketDataHistoricalClient::initializeMarketDataClient()
    {
        client = std::make_shared<databento::Historical>(MarketDataUtils::getHistoricalClient());

        auto downloaded_files = client->BatchDownload(ConfigReader::extractStringValueFromConfig("marketData"),
                                                      ConfigReader::extractStringValueFromConfig("fileToDownload"));

        for (const auto& file : downloaded_files)
        {
            if (file.substr(file.length() - 8) == ".dbn.zst")
            {
                databento::DbnFileStore dbn_store{file};
                dbn_store.Replay(processQuote);
            }
        }

        streamingClient->initialize();
    }

    std::shared_ptr<IMarketDataProvider> MarketDataHistoricalClient::getClient() const
    {
        return std::make_shared<MarketDataHistoricalClient>(*this);
    }

    void MarketDataHistoricalClient::closeClientConnection()
    {

    }
}