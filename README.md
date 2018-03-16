# sslClient

This sample will be helpfull to  send GET request to the  SSL/TLS secured host . 

## Compile

gcc -o sslClient sslclient.c -lssl -lcrypto 

## Using example
```<hostname> <port(443 or 8443)><requestBody>```



Here is the  sample  request and Response : 

Request : 
```
./sslClient raw.githubusercontent.com 443 "/yql/yql-tables/master/yahoo/finance/yahoo.finance.quotes.xml"

```

Result : 

```
--Successfully made the TCP connection to: raw.githubusercontent.com.
--Successfully enabled SSL/TLS session to: raw.githubusercontent.com.
-------------------------Server certificate---------------------------------
Subject: /C=US/ST=California/L=San Francisco/O=GitHub, Inc./CN=www.github.com
Issuer: /C=US/O=DigiCert Inc/OU=www.digicert.com/CN=DigiCert SHA2 High Assurance Server CA
-------------------------Signature------------------------------
Signature Algorithm:
sha256WithRSAEncryption

Signature Length:
256 Bytes

Signature Data:
99:7e:d6:2f:ce:1b:a6:15:f5:15:b3:ef:f1:30:c1:1f:54:10:
92:a4:8c:43:c0:bc:bd:a5:0d:00:53:e2:42:c1:85:6f:e5:a7:
a9:41:99:4b:46:11:5a:dd:fd:e8:27:69:97:b6:3c:a6:0e:2a:
30:db:33:53:be:83:b0:aa:08:89:04:7e:66:35:e5:5c:b3:2c:
28:7f:a7:b1:e5:27:79:6d:81:26:89:ea:a0:55:51:70:10:cb:
eb:43:59:6b:aa:52:b4:46:fd:d2:ff:89:16:8a:45:da:0e:bf:
87:0d:53:ef:83:24:c5:17:ad:12:63:40:74:80:4d:bd:a4:c9:
dd:74:d9:df:1c:61:02:0a:71:b0:93:24:2f:2d:a9:20:7a:43:
86:44:11:58:8a:45:9b:d7:5c:e2:66:eb:a6:c6:f1:7c:a7:dc:
dd:af:27:89:39:f7:c1:9a:99:c8:7f:34:7a:d9:39:73:83:cb:
73:75:bc:16:b0:4e:a1:49:2d:09:12:8d:4e:3e:63:ff:f0:88:
71:df:50:46:2b:a5:38:3d:db:38:08:97:29:64:de:cb:c7:eb:
88:70:59:dd:62:dc:16:76:2d:30:6a:e3:a3:2f:40:a5:36:0f:
cc:05:76:d5:e0:6e:04:40:3d:6a:21:5f:bf:4e:a3:a8:6c:d0:
98:21:b9:bd
-------------------------------------------------------
-------------------------Public-Key------------------------------
2048 bit RSA Key

-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAxtPxijvPpEXyy3Bn10Wf
oWmKTW753Uv2PusDNmalx/7mqFqi5BqK4xWQHQgSpyhedgtWIXWCJGHtgFVck+DB
AbHiHsE67ewpV1a2l2GpqNCFTU77UsoNVD/xPyx3k+cPX9y8rqjMiZB3xs1zKDYB
kcoBVrA+iO323YkJmCLEXCO2O7b1twLFWkNwMd7e7nteu2uCMvxNp5Qg22MIn33t
2egMPfIDU/TcKDfyaty5+s6F3gzh7eIgnqNQN0T/5fpaYkqdx8j21QDsIyF/CfSp
A5qKLuhluu8xrUbnc0MigX7VThS9PbfxMSQ1cQQfbGdxoQNJTNHxXv+ZTXAxKCju
5wIDAQAB
-----END PUBLIC KEY-----
------------------------------------------------------
-------------------------End Certificate---------------------------------
----------------------------------Request-----------------------------------------
Request : GET /yql/yql-tables/master/yahoo/finance/yahoo.finance.quotes.xml HTTP/1.1
Host: raw.githubusercontent.com
Connection: Close


--Connected ->Encryption:  ECDHE-RSA-AES128-GCM-SHA256 
Write-Result = 126
----------------------------end Request---------------------------------
----------------------------------Response-----------------------------------------
HTTP/1.1 200 OK
Content-Security-Policy: default-src 'none'; style-src 'unsafe-inline'; sandbox
Strict-Transport-Security: max-age=31536000
X-Content-Type-Options: nosniff
X-Frame-Options: deny
X-XSS-Protection: 1; mode=block
ETag: "d097f530622fd29a97cfc1d92219cd7845c4d04b"
Content-Type: text/plain; charset=utf-8
Cache-Control: max-age=300
X-Geo-Block-List:
X-GitHub-Request-Id: FF56:1131:17C6FF:19A70F:5AABA1F3
Content-Length: 2853
Accept-Ranges: bytes
Date: Fri, 16 Mar 2018 10:53:22 GMT
Via: 1.1 varnish
Connection: close
X-Served-By: cache-hhn1529-HHN
X-Cache: HIT
X-Cache-Hits: 1
X-Timer: S1521197603.902476,VS0,VE1
Vary: Authorization,Accept-Encoding
Access-Control-Allow-Origin: *
X-Fastly-Request-ID: 54da46a06caf5c6a859a7b05054b7702206c464d
Expires: Fri, 16 Mar 2018 10:58:22 GMT
Source-Age: 47

<?xml version="1.0" encoding="UTF-8" ?>
<table xmlns="http://query.yahooapis.com/v1/schema/table.xsd">
	<meta>
		<sampleQuery>
			select * from {table} where symbol in ("YHOO","AAPL","GOOG","MSFT")
		</sampleQuery>
	</meta>
	<bindings>
		<select itemPath="quotes.quote" produces="XML">
			<urls><url>http://download.finance.yahoo.com/d/quotes.csv?s={-listjoin|,|symbol}</url></urls>
			<inputs>
				<key id='f' type='xs:string' const='true' default='aa2bb2b3b4cc1c3c4c6c8dd1d2ee1e7e8e9ghjkg1g3g4g5g6ii5j1j3j4j5j6k1k2k4k5ll1l2l3mm2m3m4m5m6m7m8nn4opp1p2p5p6qrr1r2r5r6r7ss1s7t1t7t8vv1v7ww1w4xy' paramType='query' />
				<key id='symbol' type='xs:string' batchable='true' maxBatchItems='20' paramType='path' required='true'/>
			</inputs>
			<execute><![CDATA[
				var results = y.query("select * from csv where url=@url and columns='Ask,AverageDailyVolume,Bid,AskRealtime,BidRealtime,BookValue,Change&PercentChange,Change,Commission,Currency,ChangeRealtime,AfterHoursChangeRealtime,DividendShare,LastTradeDate,TradeDate,EarningsShare,ErrorIndicationreturnedforsymbolchangedinvalid,EPSEstimateCurrentYear,EPSEstimateNextYear,EPSEstimateNextQuarter,DaysLow,DaysHigh,YearLow,YearHigh,HoldingsGainPercent,AnnualizedGain,HoldingsGain,HoldingsGainPercentRealtime,HoldingsGainRealtime,MoreInfo,OrderBookRealtime,MarketCapitalization,MarketCapRealtime,EBITDA,ChangeFromYearLow,PercentChangeFromYearLow,LastTradeRealtimeWithTime,ChangePercentRealtime,ChangeFromYearHigh,PercebtChangeFromYearHigh,LastTradeWithTime,LastTradePriceOnly,HighLimit,LowLimit,DaysRange,DaysRangeRealtime,FiftydayMovingAverage,TwoHundreddayMovingAverage,ChangeFromTwoHundreddayMovingAverage,PercentChangeFromTwoHundreddayMovingAverage,ChangeFromFiftydayMovingAverage,PercentChangeFromFiftydayMovingAverage,Name,Notes,Open,PreviousClose,PricePaid,ChangeinPercent,PriceSales,PriceBook,ExDividendDate,PERatio,DividendPayDate,PERatioRealtime,PEGRatio,PriceEPSEstimate
CurrentYear,PriceEPSEstimateNextYear,Symbol,SharesOwned,ShortRatio,LastTradeTime,TickerTrend,OneyrTargetPrice,Volume,HoldingsValue,HoldingsValueRealtime,YearRange,DaysValueChange,DaysValueChangeRealtime,StockExchange,DividendYield'",{url:request.url});
				var quotes = <quotes/>;
				var rows=results.results.row;
				for each (var row in rows) {
					for each (var item in row.*) {
						var elname = item.localName();
						var txt = item.text().toString();
						if (txt=="N/A") txt=""; else if (txt=="-") txt=""; else {
							txt = txt.replace(/"/g, '');
						}
						row[elname]=txt;
					}
					//split % change out
					var txt = row["Change_PercentChange"].text().toString();
					row["PercentChange"]=txt.substring(txt.indexOf(" - ")+2);	
				    quotes.quote += <quote symbol={row.Symbol.text().toString()}>{row.*}</quote>;
				}
				response.object = quotes;
      ]]></execute>
		</select>
	</bindings>
</table>

---------------------------------------------------------------------------------------------
Finished SSL/TLS connection with Host: raw.githubusercontent.com.

```
