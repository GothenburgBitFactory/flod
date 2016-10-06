#!/bin/bash

curl -s -X DELETE \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $TOKEN"   \
     "https://api.digitalocean.com/v2/droplets/$1"
