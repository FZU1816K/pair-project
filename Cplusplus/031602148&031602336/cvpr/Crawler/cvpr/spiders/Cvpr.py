from scrapy.spiders import Spider
from cvpr.items import CvprItem
from scrapy import Request

def parse_detail (response):
    item = CvprItem()
    item['Title'] = response.xpath('//div[@id="content"]//dd/div[@id="papertitle"]/text()').extract()
    item['Abstract'] = response.xpath('//div[@id="content"]//dd/div[@id="abstract"]/text()').extract()

    yield item

class CvprSpider(Spider):
    name="cvpr"
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36',
    }

    def start_requests(self):
        url='http://openaccess.thecvf.com/CVPR2018.py'
        yield Request(url,headers=self.headers)

    def parse(self,response):
        links= response.xpath('//div[@id="content"]//dt//a/@href').extract()
        for link in links:
            link = 'http://openaccess.thecvf.com/'+link
            yield Request(link,headers=self.headers,callback=parse_detail)


