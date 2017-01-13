/* tag.h
   Mathieu Stefani, 12 november 2016
   
   A typed list of FIX tags
*/

#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <tuple>

namespace Fix
{
    namespace Type
    {
        template<typename T>
        struct Base
        {
            using UnderlyingType = T;

            Base() { }

            Base(T);
        };

        struct Char : public Base<char>
        {
            using Base::Base;
        };

        struct Boolean
        {
            struct Boxed
            {
                Boxed(bool value = false)
                    : m_value(value)
                { }

                Boxed(const Boxed& other) = default;
                Boxed(Boxed&& other) = default;

                Boxed& operator=(const Boxed& other) = default;
                Boxed& operator=(Boxed&& other) = default;

                operator bool() const
                {
                    return m_value;
                }

            private:
                bool m_value;
            };

            using UnderlyingType = Boxed;

            Boolean(bool);
            Boolean(const Boxed&);
        };

        struct Float : public Base<float>
        {
            using Base::Base;
        };

        using Amt = Float;
        using Price = Float;
        using Qty = Float;

        struct Int : public Base<int>
        {
            using Base::Base;
        };

        struct Data
        {
            using UnderlyingType = std::string;

            Data(const std::string&);
            Data(const char *);
        };

        struct String : public Base<std::string>
        {
            using Base::Base;

            String(const char*);
        };

        using MultipleValueString = Type::String;

        using DayOfMonth = Int;
        using MonthYear = String;

        struct UTCTimestamp
        {
            struct Time
            {
                Time()
                    : m_time(std::time(nullptr))
                { }

                Time(const std::time_t& time)
                    : m_time(time)
                { }

                std::time_t time() const
                {
                    return m_time;
                }

            private:
                std::time_t m_time;
            };

            using UnderlyingType = Time;

            UTCTimestamp(const std::string &);
            UTCTimestamp(const Time&);
            UTCTimestamp(const std::time_t&);
        };

        std::ostream& operator<<(std::ostream& os, const UTCTimestamp::Time& value)
        {
            auto time = value.time();
            char buffer[32];
            strftime(buffer, sizeof buffer, "%Y%m%d-%H%M%S", std::gmtime(&time)); 
            os << buffer;
            return os;
        }

        std::ostream& operator<<(std::ostream& os, const Boolean::Boxed& value)
        {
            os << (value ? 'Y' : 'N');
            return os;
        }

        using LocalMktDate = String;
        using UTCDate = String;
        using UTCTimeOnly = String;

    } // namespace Type

    template<unsigned N, typename T> struct TagT
    {
        static constexpr unsigned Id = N;

        using Type = T;
    };


    namespace Tag
    {
        using Account = TagT<1, Type::String>;
        using AdvId = TagT<2, Type::String>;
        using AdvRefID = TagT<3, Type::String>;
        using AdvSide = TagT<4, Type::Char>;
        using AdvTransType = TagT<5, Type::String>;
        using AvgPx = TagT<6, Type::Float>;
        using BeginSeqNo = TagT<7, Type::Int>;
        using BeginString = TagT<8, Type::String>;
        using BodyLength = TagT<9, Type::Int>;
        using CheckSum = TagT<10, Type::String>;
        using ClOrdID = TagT<11, Type::String>;
        using Commission = TagT<12, Type::Amt>;
        using CommType  = TagT<13, Type::Char>;
        using CumQty = TagT<14, Type::Qty>;
        using Currency = TagT<15, Type::String>;
        using EndSeqNo = TagT<16, Type::Int>;
        using ExecID  = TagT<17, Type::String>;
        using ExecInst = TagT<18, Type::MultipleValueString>;
        using ExecRefID = TagT<19, Type::String>;
        using ExecTransType = TagT<20, Type::Char>;
        using HandlInst = TagT<21, Type::Char>;
        using IDSource = TagT<22, Type::String>;
        using SecurityIDSource = IDSource;
        using IOIid = TagT<23, Type::String>;

        using IOIQltyInd = TagT<25, Type::Char>;
        using IOIRefID = TagT<26, Type::String>;
        using IOIShares = TagT<27, Type::String>;
        using IOITransType = TagT<28, Type::Char>;
        using LastCapacity = TagT<29, Type::Char>;
        using LastMkt = TagT<30, Type::String>;
        using LastPx = TagT<31, Type::Price>;
        using LastShares = TagT<32, Type::Qty>;
        using LinesOfText = TagT<33, Type::Int>;
        using MsgSeqNum = TagT<34, Type::Int>;
        using MsgType = TagT<35, Type::String>;
        using NewSeqNo = TagT<36, Type::Int>;
        using OrderID = TagT<37, Type::String>;
        using OrderQty = TagT<38, Type::Qty>;
        using OrdStatus = TagT<39, Type::Char>;
        using OrdType = TagT<40, Type::Char>;
        using OrigClOrdID = TagT<41, Type::String>;
        using OrigTime  = TagT<42, Type::UTCTimestamp>;
        using PossDupFlag = TagT<43, Type::Boolean>;
        using Price = TagT<44, Type::Float>;
        using RefSeqNum = TagT<45, Type::Int>;
        using SecurityID = TagT<48, Type::String>;
        using SenderCompID = TagT<49, Type::String>;
        using SenderSubID = TagT<50, Type::String>;
        using SendingTime = TagT<52, Type::UTCTimestamp>;
        using Side = TagT<54, Type::Char>;
        using Symbol = TagT<55, Type::String>;
        using TargetCompID = TagT<56, Type::String>;
        using TargetSubID = TagT<57, Type::String>;
        using Text = TagT<58, Type::String>;
        using TimeInForce = TagT<59, Type::Char>;
        using TransactTime = TagT<60, Type::UTCTimestamp>;
        using ValidUntilTime = TagT<62, Type::UTCTimestamp>;
        using SettlmntTyp = TagT<63, Type::Char>;
        using FutSettDate = TagT<64, Type::LocalMktDate>;
        using SymbolSfx = TagT<65, Type::String>;
        using SecureDataLen = TagT<90, Type::Int>;
        using SecureData = TagT<91, Type::Data>;
        using RawDataLength = TagT<95, Type::Int>;
        using RawData = TagT<96, Type::Data>;
        using PossResend = TagT<97, Type::Boolean>;
        using EncryptMethod = TagT<98, Type::Int>;
        using IOIQualifier = TagT<104, Type::Char>;
        using Issuer = TagT<106, Type::String>;
        using SecurityDesc = TagT<107, Type::String>;
        using HeartBtInt = TagT<108, Type::Int>;
        using MinQty = TagT<110, Type::Qty>;
        using TestReqID = TagT<112, Type::String>;
        using OnBehalfOfCompID = TagT<115, Type::String>;
        using OnBehalfOfSubID = TagT<116, Type::String>;
        using QuoteID = TagT<117, Type::String>;
        using OrigSendingTime = TagT<122, Type::UTCTimestamp>;
        using GapFillFlag = TagT<123, Type::Boolean>;
        using ExpireTime = TagT<126, Type::UTCTimestamp>;
        using DeliverToCompID = TagT<128, Type::String>;
        using DeliverToSubID = TagT<129, Type::String>;
        using IOINaturalFlag = TagT<130, Type::Boolean>;
        using QuoteReqID = TagT<131, Type::String>;
        using BidPx = TagT<132, Type::Price>;
        using OfferPx = TagT<133, Type::Price>;
        using BidSize = TagT<134, Type::Qty>;
        using OfferSize = TagT<135, Type::Qty>;
        using ResetSeqNumFlag = TagT<141, Type::Boolean>;
        using SenderLocationID = TagT<142, Type::String>;
        using TargetLocationID = TagT<143, Type::String>;
        using OnBehalfOfLocationID = TagT<144, Type::String>;
        using DeliverToLocationID = TagT<145, Type::String>;
        using NoRelatedSym = TagT<146, Type::Int>;
        using URLLink = TagT<149, Type::String>;
        using SecurityType = TagT<167, Type::String>;
        using BidSpotRate = TagT<188, Type::Price>;
        using BidForwardPoints = TagT<189, Type::Price>;
        using OfferSpotRate = TagT<190, Type::Price>;
        using OfferForwardPoints = TagT<191, Type::Price>;
        using OrderQty2 = TagT<192, Type::Qty>;
        using FutSettDate2 = TagT<193, Type::LocalMktDate>;
        using NoIOIQualifiers = TagT<199, Type::Int>;
        using MaturityMonthYear = TagT<200, Type::MonthYear>;
        using PutOrCall = TagT<201, Type::Int>;
        using StrikePrice = TagT<202, Type::Float>;
        using MaturityDay = TagT<205, Type::DayOfMonth>;
        using OptAttribute = TagT<206, Type::Char>;
        using SecurityExchange = TagT<207, Type::String>;
        using XmlDataLen = TagT<212, Type::Int>;
        using XmlData = TagT<213, Type::Data>;
        using NoRoutingIDs = TagT<215, Type::Int>;
        using RoutingType = TagT<216, Type::Int>;
        using RoutingID = TagT<217, Type::String>;
        using SpreadToBenchmark = TagT<218, Type::Float>;
        using Benchmark = TagT<219, Type::Char>;
        using CouponRate = TagT<223, Type::Float>;
        using CouponPaymentDate = TagT<224, Type::LocalMktDate>;
        using IssueDate = TagT<225, Type::LocalMktDate>;
        using RepurchaseTerm = TagT<226, Type::Int>;
        using RepurchaseRate = TagT<227, Type::Float>;
        using Factor = TagT<228, Type::Float>;
        using ContractMultiplier = TagT<231, Type::Float>;
        using RepoCollateralSecurityType = TagT<239, Type::Int>;
        using RedemptionDate = TagT<240, Type::LocalMktDate>;
        using UnderlyingCouponPaymentDate = TagT<241, Type::LocalMktDate>;
        using UnderlyingIssueDate = TagT<242, Type::LocalMktDate>;
        using UnderlyingRepoCollateralSecurityType = TagT<243, Type::Int>;
        using UnderlyingRepurchaseTerm  = TagT<244, Type::Int>;
        using UnderlyingRepurchaseRate = TagT<245, Type::Float>;
        using UnderlyingFactor = TagT<246, Type::Float>;
        using LegCouponPaymentDate = TagT<248, Type::LocalMktDate>;
        using UnderlyingRedemptionDate = TagT<247, Type::LocalMktDate>;
        using LegIssueDate = TagT<249, Type::LocalMktDate>;
        using LegRepoCollateralSecurityType = TagT<250, Type::Int>;
        using LegRepurchaseTerm = TagT<251, Type::Int>;
        using LegRepurchaseRate = TagT<252, Type::Float>;
        using LegFactor = TagT<253, Type::Float>;
        using LegRedemptionDate = TagT<254, Type::LocalMktDate>;
        using CreditRating = TagT<255, Type::String>;
        using UnderlyingCreditRating = TagT<256, Type::String>;
        using LegCreditRating = TagT<257, Type::String>;
        using MDReqID = TagT<262, Type::String>;
        using SubscriptionRequestType = TagT<263, Type::Char>;
        using MarketDepth = TagT<264, Type::Int>;
        using MDUpdateType = TagT<265, Type::Int>;
        using AggregatedBook = TagT<266, Type::Boolean>;
        using NoMDEntryTypes = TagT<267, Type::Int>;
        using NoMDEntries = TagT<268, Type::Int>;
        using MDEntryType = TagT<269, Type::Char>;
        using MDEntryPx = TagT<270, Type::Price>;
        using MDEntrySize = TagT<271, Type::Qty>;
        using MDEntryDate = TagT<272, Type::UTCDate>;
        using MDEntryTime = TagT<273, Type::UTCTimeOnly>;
        using TickDirection = TagT<274, Type::Char>;
        using MDMkt = TagT<275, Type::String>;
        using QuoteCondition = TagT<276, Type::MultipleValueString>;
        using TradeCondition = TagT<277, Type::MultipleValueString>;
        using MDEntryID = TagT<278, Type::String>;
        using MDUpdateAction = TagT<279, Type::Char>;
        using MDEntryRefID = TagT<280, Type::String>;
        using MDEntryOriginator = TagT<282, Type::String>;
        using LocationID = TagT<283, Type::String>;
        using DeskID = TagT<284, Type::String>;
        using DeleteReason = TagT<285, Type::Char>;
        using OpenCloseSettleFlag = TagT<286, Type::Char>;
        using SellerDays = TagT<287, Type::Int>;
        using MDEntryBuyer = TagT<288, Type::String>;
        using MDEntrySeller = TagT<289, Type::String>;
        using MDEntryPositionNo = TagT<290, Type::Int>;
        using FinancialStatus = TagT<291, Type::Char>;
        using CorporateAction = TagT<292, Type::Char>;
        using QuoteEntryID = TagT<299, Type::String>;
        using QuoteResponseLevel = TagT<301, Type::Int>;
        using QuoteResponseType = TagT<303, Type::Int>;
        using UnderlyingIssuer = TagT<306, Type::String>;
        using UnderlyingSecurityExchange = TagT<308, Type::String>;
        using UnderlyingSecurityID = TagT<309, Type::String>;
        using UnderlyingSecurityIDSource = TagT<305, Type::String>;
        using UnderlyingSecurityDesc = TagT<307, Type::String>;
        using UnderlyingSecurityType = TagT<310, Type::String>;
        using UnderlyingSymbol = TagT<311, Type::String>;
        using UnderlyingSymbolSfx = TagT<312, Type::String>;
        using UnderlyingMaturityMonthYear = TagT<313, Type::String>;
        using UnderlyingStrikePrice = TagT<316, Type::Price>;
        using UnderlyingOptAttribute = TagT<317, Type::Char>;
        using UnderlyingCurrency = TagT<318, Type::String>;
        using TradingSessionID = TagT<336, Type::String>;
        using MessageEncoding = TagT<347, Type::String>;
        using EncodedSecurityDescLen = TagT<350, Type::Int>;
        using EncodedSecurityDesc = TagT<351, Type::Data>;
        using EncodedTextLen = TagT<354, Type::Int>;
        using EncodedText = TagT<355, Type::Data>;
        using NumberOfOrders = TagT<346, Type::Int>;
        using EncodedIssuerLen = TagT<348, Type::Int>;
        using EncodedIssuer = TagT<349, Type::Data>;
        using EncodedUnderlyingIssuerLen = TagT<362, Type::Int>;
        using EncodedUnderlyingIssuer = TagT<363, Type::Data>;
        using EncodedUnderlyingSecurityDescLen = TagT<364, Type::Int>;
        using EncodedUnderlyingSecurityDesc = TagT<365, Type::Data>;
        using LastMsgSeqNumProcessed = TagT<369, Type::Int>;
        using OnBehalfOfSendingTime = TagT<370, Type::UTCTimestamp>; 
        using RefTagID = TagT<371, Type::Int>;
        using RefMsgType = TagT<372, Type::String>;
        using SessionRejectReason = TagT<373, Type::Int>;
        using MaxMessageSize = TagT<383, Type::Int>;
        using NoMsgTypes = TagT<384, Type::Int>;
        using MsgDirection = TagT<385, Type::Char>;
        using TotalVolumeTraded = TagT<387, Type::Qty>;
        using UnderlyingCouponRate = TagT<435, Type::Float>;
        using UnderlyingContractMultiplier = TagT<436, Type::Float>;
        using ExpireDate = TagT<432, Type::String>;
        using NetChgPrevDay = TagT<451, Type::Float>;
        using NoSecurityAltID = TagT<454, Type::Int>;
        using SecurityAltID = TagT<455, Type::String>;
        using SecurityAltIDSource = TagT<456, Type::String>;
        using NoUnderlyingSecurityAltID = TagT<457, Type::Int>;
        using UnderlyingSecurityAltID = TagT<458, Type::String>;
        using UnderlyingSecurityAltIDSource = TagT<459, Type::String>;
        using Product = TagT<460, Type::Int>;
        using CFICode = TagT<461, Type::String>;
        using UnderlyingProduct = TagT<462, Type::Int>;
        using UnderlyingCFICode = TagT<463, Type::String>;
        using CountryOfIssue = TagT<470, Type::String>;
        using StateOrProvinceOfIssue = TagT<471, Type::String>;
        using LocaleOfIssue = TagT<472, Type::String>;
        using MaturityDate = TagT<541, Type::LocalMktDate>;
        using UnderlyingMaturityDate = TagT<542, Type::LocalMktDate>;
        using InstrRegistry = TagT<543, Type::String>;
        using Scope = TagT<546, Type::MultipleValueString>;
        using NoLegs = TagT<555, Type::Int>;
        using LegCurrency = TagT<556, Type::String>;
        using UnderlyingCountryOfIssue = TagT<592, Type::String>;
        using UnderlyingStateOrProvinceOfIssue = TagT<593, Type::String>;
        using UnderlyingLocaleOfIssue = TagT<594, Type::String>;
        using UnderlyingInstrRegistry = TagT<595, Type::String>;
        using LegCountryOfIssue = TagT<596, Type::String>;
        using LegStateOrProvinceOfIssue = TagT<597, Type::String>;
        using LegLocaleOfIssue = TagT<598, Type::String>;
        using LegInstrRegistry = TagT<599, Type::String>;
        using LegSymbol = TagT<600, Type::String>;
        using LegSymbolSfx = TagT<601, Type::String>;
        using LegSecurityID = TagT<602, Type::String>;
        using LegSecurityIDSource = TagT<603, Type::String>;
        using NoLegSecurityAltID = TagT<604, Type::Int>;
        using LegSecurityAltID = TagT<605, Type::String>;
        using LegSecurityAltIDSource = TagT<606, Type::String>;
        using LegProduct = TagT<607, Type::Int>;
        using LegCFICode = TagT<608, Type::String>;
        using LegSecurityType = TagT<609, Type::String>;
        using LegMaturityMonthYear = TagT<610, Type::String>;
        using LegMaturityDate = TagT<611, Type::LocalMktDate>;
        using LegStrikePrice = TagT<612, Type::Price>;
        using LegOptAttribute = TagT<613, Type::Char>;
        using LegContractMultiplier = TagT<614, Type::Float>;
        using LegCouponRate = TagT<615, Type::Float>;
        using LegSecurityExchange = TagT<616, Type::String>;
        using LegIssuer = TagT<617, Type::String>;
        using EncodedLegIssuerLen = TagT<618, Type::Int>;
        using EncodedLegIssuer = TagT<619, Type::Data>;
        using LegSecurityDesc = TagT<620, Type::String>;
        using EncodedLegSecurityDescLen = TagT<621, Type::Int>;
        using EncodedLegSecurityDesc = TagT<622, Type::Data>;
        using LegRatioQty = TagT<623, Type::Float>;
        using LegSide = TagT<624, Type::Char>;
        using TradingSessionSubID = TagT<625, Type::String>;
        using ContractSettlMonth = TagT<667, Type::String>;
        using Pool = TagT<691, Type::String>;
        using NoUnderlyings = TagT<711, Type::Int>;
        using LegDatedDate = TagT<739, Type::LocalMktDate>;
        using LegPool = TagT<740, Type::String>;
        using SecuritySubType = TagT<762, Type::String>;
        using UnderlyingSecuritySubType = TagT<763, Type::String>;
        using LegSecuritySubType = TagT<764, Type::String>;
        using UnderlyingPx = TagT<810, Type::Price>;
        using PriceDelta = TagT<811, Type::Float>;
        using ApplQueueDepth = TagT<813, Type::Int>;
        using ApplQueueResolution = TagT<814, Type::Int>;
        using NoEvents = TagT<864, Type::Int>;
        using EventType = TagT<865, Type::Int>;
        using EventDate = TagT<866, Type::LocalMktDate>;
        using EventPx = TagT<867, Type::Price>;
        using EventText = TagT<868, Type::String>;
        using DatedDate = TagT<873, Type::LocalMktDate>;
        using InterestAccrualDate = TagT<874, Type::LocalMktDate>;
        using CPProgram = TagT<875, Type::Int>;
        using CPRegType = TagT<876, Type::String>;
        using UnderlyingCPProgram = TagT<877, Type::String>;
        using UnderlyingCPRegType = TagT<878, Type::String>;
        using UnderlyingQty = TagT<879, Type::Qty>;
        using UnderlyingDirtyPrice = TagT<882, Type::Price>;
        using UnderlyingEndPrice = TagT<883, Type::Price>;
        using UnderlyingStartValue = TagT<884, Type::Float>;
        using UnderlyingCurrentValue = TagT<885, Type::Float>;
        using UnderlyingEndValue = TagT<886, Type::Float>;
        using NoUnderlyingStips = TagT<887, Type::Int>;
        using UnderlyingStipType = TagT<888, Type::String>;
        using UnderlyingStipValue = TagT<889, Type::String>;
        using UnderlyingStrikeCurrency = TagT<941, Type::String>;
        using LegStrikeCurrency = TagT<942, Type::String>;
        using StrikeCurrency = TagT<947, Type::String>;
        using LegContractSettlMonth = TagT<955, Type::String>;
        using LegInterestAccrualDate = TagT<956, Type::String>;

    } // namespace Tag

} // namespace Fix

