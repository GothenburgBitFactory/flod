#!/bin/bash

curl -s -X GET \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $TOKEN"   \
     "https://api.digitalocean.com/v2/$1"
