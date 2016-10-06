#!/bin/bash

curl -s -X GET \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $TOKEN"   \
     "https://api.digitalocean.com/v2/droplets/$1/actions" | jq '.actions[]|{type: .type,status: .status,started_at: .started_at, complete_at: .completed_at}'
