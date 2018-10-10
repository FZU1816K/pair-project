# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/items.html

import scrapy

class CvprItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    Title=scrapy.Field()
    Abstract=scrapy.Field()

    pass
