# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html
import codecs
import os
import json
import pymysql

class CvprPipeline(object):
    def process_item(self, item, spider):
        fp=open('result.txt','w',encoding='utf-8')
        fp.write(item['Title'])
        fp.close()
        return item

