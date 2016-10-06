#!/bin/bash

curl -s -X GET \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $TOKEN"   \
     "https://api.digitalocean.com/v2/droplets" | jq '.droplets[]|{name: .name,id: .id,os: .image.slug,ip: .networks.v4[].ip_address}'
